import scipy.stats as sc
import numpy as np
import scipy 



def unwrap_data(x):
    x = np.array(x)
    x = (x+np.pi)*1440/(2*np.pi)
    return x

def wrap_data(x):
    x = np.array(x)
    x = (2*np.pi*x/1440)-np.pi
    return x

def sigma_circ(x):
    x = np.array(x)
    C = sum(np.cos(x))
    S = sum(np.sin(x))
    R = ((S**2+C**2)**0.5)/len(x)
    return 180/np.pi*(2*(1-R))**(0.5)

def bandwidth(x):
    x = np.array(x)
    n = len(x)
    IQR = sc.iqr(x)
    return 0.9*min(sigma_circ(x), IQR/1.349)/(n**(1/5))

def vonmises_pdf(x, mu, kappa, h):
    return np.exp(kappa * np.cos((x - mu)/h)) / (2. * np.pi * h * scipy.special.i0(kappa))

def vonmises_fft_kde(data, n_bins):
    bins = np.linspace(-np.pi, np.pi, n_bins + 1, endpoint=True)
    hist_n, bin_edges = np.histogram(data, bins=bins)
    bin_centers = np.mean([bin_edges[1:], bin_edges[:-1]], axis=0)
    kernel = vonmises_pdf(
        x=bin_centers,
        mu=0,
        kappa=50,
        h = 1
    )
    kde = np.fft.fftshift(np.fft.irfft(np.fft.rfft(kernel) * np.fft.rfft(hist_n)))
    kde /= np.trapz(kde, x=bin_centers)
    return  kde

def circular_kde(_data):
    n_bins = 1440
    kde2 = vonmises_fft_kde(
        data = wrap_data(_data),
        n_bins=n_bins
    )
    return kde2

def main():
    pass

if __name__ == '__main__':
    main()

